package sample

import (
	grpcgo "github.com/ShreyasJenner/grpcgo/pb"
	"google.golang.org/protobuf/types/known/timestamppb"
)

func NewChatting() *grpcgo.Chatting {
	chat := &grpcgo.Chatting{
		SendUserId: randomUserId(),
		RecvUserId: randomUserId(),
		Msg:        NewMessage(),
		Time:       timestamppb.Now(),
	}

	return chat
}

func NewMessage() *grpcgo.Msg {
	msg := &grpcgo.Msg{
		SendUsername: randomUsername(),
		RecvUsername: randomUsername(),
		Msg:          randomMessage(),
	}

	return msg
}
