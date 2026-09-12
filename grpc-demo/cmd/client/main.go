package main

import (
	"log"

	"github.com/ShreyasJenner/grpc-demo/client"
)

func main() {
	if err := client.Run("localhost:50051", "World"); err != nil {
		log.Fatalf("client failed: %v", err)
	}
}
