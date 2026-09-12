package server

import (
	"context"
	"log"
	"net"

	"github.com/ShreyasJenner/grpc-demo/pb"
	"google.golang.org/grpc"
	"google.golang.org/grpc/reflection"
)

type server struct {
	pb.UnimplementedGreeterServer
}

func (s *server) SayHello(ctx context.Context, req *pb.HelloRequest) (*pb.HelloReply, error) {
	log.Printf("Received request from: %s", req.GetName())

	reply := &pb.HelloReply{
		Message: "Server says hello, " + req.GetName() + "!",
	}

	return reply, nil
}

func Run(port string) error {
	lis, err := net.Listen("tcp", ":"+port)
	if err != nil {
		return err
	}

	grpcServer := grpc.NewServer()
	pb.RegisterGreeterServer(grpcServer, &server{})

	reflection.Register(grpcServer)

	log.Printf("gRPC server listening on: %s", port)
	return grpcServer.Serve(lis)
}
