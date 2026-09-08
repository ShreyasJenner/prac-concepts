package sample

import "math/rand"

// return a random userid below 100
func randomUserId() int32 {
	return rand.Int31() % 100
}

func randomUsername() string {
	return randomStrings("User1", "User2", "User3", "User4", "User5")
}

func randomMessage() string {
	return randomStrings("hi", "how are you doing?", "offering full time jobs with no pay",
		"welcome to reality", "good bye")
}

func randomStrings(a ...string) string {
	n := len(a)
	if n == 0 {
		return ""
	}
	return a[rand.Intn(n)]
}
