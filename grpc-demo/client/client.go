package client

import (
	"context"
	"log"
	"time"

	"github.com/ShreyasJenner/grpc-demo/pb"
	"google.golang.org/grpc"
	"google.golang.org/grpc/credentials/insecure"
)

func Run(address string, name string) error {
	conn, err := grpc.NewClient(address, grpc.WithTransportCredentials(insecure.NewCredentials()))
	if err != nil {
		return err
	}
	defer conn.Close()

	client := pb.NewGreeterClient(conn)

	ctx, cancel := context.WithTimeout(context.Background(), 5*time.Second)
	defer cancel()

	reply, err := client.SayHello(ctx, &pb.HelloRequest{Name: name})
	if err != nil {
		return err
	}

	log.Printf("Server replied: %s", reply.GetMessage())
	return nil
}
