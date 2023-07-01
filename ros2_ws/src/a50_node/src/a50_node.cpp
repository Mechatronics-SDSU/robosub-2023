/* 
 * @author Zix
 * A50 sensor is the love of my life and gives a lot of information
 * That data can be grabbed from a web server using tcp/ip (sockets baby)
 * Here we will take that information, parse the json for what we want, and regurgitate it out
 * Of course in C++ because I'm tired of trash languages in this code base 
 */

#include <chrono>
#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>
#include <stdexcept>
#include <nlohmann/json.hpp>        // I love this library more than my own mother

#include "control_interface.hpp"
#include "rclcpp/rclcpp.hpp"
#include "scion_types/msg/state.hpp"
#include "vector_operations.hpp"

using namespace std;
using json = nlohmann::json;

class A50Node : public rclcpp::Node
{
public:
  explicit A50Node()
    : Node("dvl_node")
  {
    position_publisher_ = this->create_publisher<scion_types::msg::State>("a50_state_data", 10);
    orientation_publisher_ = this->create_publisher<scion_types::msg::State>("ahrs_orientation_data", 10);
    this->startListener();
  }

private:
    const char* TCP_IP = "192.168.1.4";
    const int   TCP_PORT = 16171;
    const int   BUFFER_SIZE = 2048;
    Interface::state_pub_t position_publisher_;
    Interface::state_pub_t orientation_publisher_;

    void startListener()
    {
        int sock = 0;
        struct sockaddr_in serv_addr;
        char buffer[BUFFER_SIZE] = {0};
        
        while (true) 
        {
            sock = connectToSocket(sock, serv_addr);
            ssize_t bytesRead = recv(sock, buffer, BUFFER_SIZE, 0);
            std::string json_stream(buffer, bytesRead);
            json json_dict = json::parse(json_stream);
            vector<float> a50_data = parseJson(json_dict);
            if (!a50_data.empty()) {publishData(a50_data);}
        }
    }

    int connectToSocket(int sock, struct sockaddr_in& serv_addr) 
    {
        if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
            throw std::runtime_error("Socket creation error");
        }

        serv_addr.sin_family = AF_INET;
        serv_addr.sin_port = htons(TCP_PORT);

        if (inet_pton(AF_INET, TCP_IP, &serv_addr.sin_addr) <= 0) {
        throw std::runtime_error("Invalid address/ Address not supported");
        }

        if (connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0) {
        throw std::runtime_error("Connection Failed");
        }
        return sock;
    }

    vector<float> parseJson(json json_dict) 
    {
        float x, y, z, yaw, pitch, roll;
        try {
            x = json_dict["x"];
            y = json_dict["y"];
            z = json_dict["z"];
            yaw = json_dict["yaw"];
            pitch = json_dict["pitch"];
            roll = json_dict["roll"];
        } catch (...) {
            return vector<float>{};
        }
        return vector<float>{yaw, pitch, roll, x, y, z};
    }

    void publishData(vector<float>& a50_data) 
    {
        auto orientation = scion_types::msg::State();
        orientation.state = {a50_data[0], a50_data[1], a50_data[2]};
        orientation_publisher_->publish(orientation);

        auto position = scion_types::msg::State();
        position.state = {a50_data[3], a50_data[4], a50_data[5]};
        position_publisher_->publish(position);

        RCLCPP_INFO(this->get_logger(), "Publishing State Data: \nx: %f\ny: %f\nz: %f\n",
                    position.state[0], position.state[1], position.state[2]);
        RCLCPP_INFO(this->get_logger(), "Publishing State Data: \nyaw: %f\npitch: %f\nroll: %f\n",
                    orientation.state[0], orientation.state[1], orientation.state[2]);
    }
};

int main(int argc, char* argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<A50Node>());
  rclcpp::shutdown();
  return 0;
}