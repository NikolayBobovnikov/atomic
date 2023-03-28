#include "employee.grpc.pb.h"
#include "employee.h"
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
using proto::Employees;

using namespace std;

class EmployeesClient
{
public:
  EmployeesClient(shared_ptr<Channel> channel) : stub_(Employees::NewStub(channel)) {}

  // Assembles the client's payload, sends it and presents the response back
  // from the server.
  void InsertEmployee(const string &name, const string &position)
  {
    // Data we are sending to the server.
    proto::Employee employee;
    employee.set_name(name);
    employee.set_position(position);

    // Container for the data we expect from the server.
    proto::EmployeeId reply;

    // Context for the client. It could be used to convey extra information to
    // the server and/or tweak certain RPC behaviors.
    ClientContext context;

    // The actual RPC.
    Status status = stub_->InsertEmployee(&context, employee, &reply);

    // Act upon its status.
    if (!status.ok())
    {
      cout << "RPC failed with code" << status.error_code() << ": " << status.error_message() << endl;
      return;
    }
    cout << "OK" << endl;
  }

private:
  unique_ptr<Employees::Stub> stub_;
};

int
main(int argc, char **argv)
{
  EmployeesClient client(grpc::CreateChannel("localhost:50051", grpc::InsecureChannelCredentials()));
  client.InsertEmployee("EmployeeName", "Senior dev");
  return 0;
}
