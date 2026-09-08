package serializer

import (
	"fmt"
	"os"

	"google.golang.org/protobuf/proto"
)

func WriteProtobufToJSONFile(msg proto.Message, filename string) error {
	data, err := ProtobufToJSON(msg)
	if err != nil {
		return fmt.Errorf("cannot marshal proto msg to binary: %w", err)
	}

	err = os.WriteFile(filename, []byte(data), 0644)
	if err != nil {
		return fmt.Errorf("cant write json data to file: %w", err)
	}
	return nil
}

func WriteProtobufToBinaryFile(msg proto.Message, filename string) error {
	data, err := proto.Marshal(msg)
	if err != nil {
		return fmt.Errorf("cannot marshal message")
	}

	err = os.WriteFile(filename, data, 0644)
	if err != nil {
		return fmt.Errorf("cannot write binary data to file")
	}

	return nil
}

func ReadProtobufFromBinaryFile(filename string, msg proto.Message) error {
	data, err := os.ReadFile(filename)
	if err != nil {
		return fmt.Errorf("can't read binary file with error: %w", err)
	}

	err = proto.Unmarshal(data, msg)
	if err != nil {
		return fmt.Errorf("unable to unmarshal data read from binary file with error: %w", err)
	}

	return nil
}
