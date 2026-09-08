package serializer_test

import (
	"testing"

	"github.com/ShreyasJenner/grpcgo/sample"
	"github.com/ShreyasJenner/grpcgo/serializer"
	"github.com/stretchr/testify/require"
	"google.golang.org/protobuf/proto"
)

func TestFileSerialze(t *testing.T) {
	t.Parallel()

	binaryFile := "../tmp/chat.bin"
	jsonFile := "../tmp/chat.json"
	chat1 := sample.NewChatting()
	err := serializer.WriteProtobufToBinaryFile(chat1, binaryFile)
	require.NoError(t, err)

	chat2 := sample.NewChatting()
	err = serializer.ReadProtobufFromBinaryFile(binaryFile, chat2)
	require.NoError(t, err)
	require.True(t, proto.Equal(chat1, chat2))

	err = serializer.WriteProtobufToJSONFile(chat1, jsonFile)
	require.NoError(t, err)
}
