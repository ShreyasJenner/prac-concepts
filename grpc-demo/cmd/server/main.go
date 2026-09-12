package main

import (
	"log"

	"github.com/ShreyasJenner/grpc-demo/server"
)

func main() {
	if err := server.Run("50051"); err != nil {
		log.Fatalf("server failed: %v", err)
	}
}
