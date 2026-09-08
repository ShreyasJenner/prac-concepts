package serializer

import (
	"google.golang.org/protobuf/encoding/protojson"
	"google.golang.org/protobuf/proto"
)

func ProtobufToJSON(msg proto.Message) (string, error) {
	marshal := protojson.Format(msg)

	return marshal, nil
}
