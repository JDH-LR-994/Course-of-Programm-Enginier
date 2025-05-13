package main

import (
	"fmt"
	"strings"
)

func main() {
	var a string
	fmt.Scan(&a)
	fmt.Printf(ReverseLetters(a))
}

func ReverseLetters(s string) string {
	var str strings.Builder
	for i := len(s) - 1; i > -1; i-- {
		if (s[i] >= 'a' && s[i] <= 'z') || (s[i] >= 'A' && s[i] <= 'Z') {
			str.WriteString(string(s[i]))
		}
	}
	return str.String()
}
