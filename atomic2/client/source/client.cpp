#include "employee.grpc.pb.h"
#include <chrono>
#include <grpc/grpc.h>
#include <grpcpp/channel.h>
#include <grpcpp/client_context.h>
#include <grpcpp/create_channel.h>
#include <grpcpp/security/credentials.h>
#include <iostream>
#include <memory>
#include <random>
#include <string>
#include <thread>

using grpc::Channel;
using grpc::ClientContext;
using grpc::ClientReader;
using grpc::ClientReaderWriter;
using grpc::ClientWriter;
using grpc::Status;
using workers::Employees;

class EmployeesClient
{
public:
  EmployeesClient(std::shared_ptr<Channel> channel, const std::string &db) : stub_(Employees::NewStub(channel)) {}

private:
  std::unique_ptr<Employees::Stub> stub_;
};

int
main(int argc, char **argv)
{
  // TODO
  std::string db = "path to db";

  EmployeesClient guide(grpc::CreateChannel("localhost:50051", grpc::InsecureChannelCredentials()), db);

  return 0;
}
