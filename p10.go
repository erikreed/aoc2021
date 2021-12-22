package main

import (
	"bufio"
	"fmt"
	"os"
)

/*
): 3 points.
]: 57 points.
}: 1197 points.
>: 25137 points.
*/
func scoreLookup(c byte) int {
	if c == ')' {
		return 3
	}
	if c == ']' {
		return 57
	}
	if c == '}' {
		return 1197
	}
	if c == '>' {
		return 25137
	}
	panic("Unknown char")
}

func closing(c byte) bool {
	return c == ')' || c == ']' || c == '}' || c == '>'
}

func flipped(c byte) byte {
	if c == ')' {
		return '('
	}
	if c == ']' {
		return '['
	}
	if c == '}' {
		return '{'
	}
	if c == '>' {
		return '<'
	}
	panic("Unknown char")
}

func main() {
	file, err := os.Open("p10.txt")
	if err != nil {
		panic(err)
	}
	reader := bufio.NewScanner(file)
	var errorSum int64 = 0

	for reader.Scan() {
		line := reader.Text()
		var chars []byte
		for i := 0; i < len(line); i++ {
			b := line[i]
			if closing(b) {
				bFlipped := flipped(b)
				if len(chars) == 0 || chars[len(chars)-1] != bFlipped {
					errorSum += int64(scoreLookup(b))
					break
				}
				chars = chars[:len(chars)-1]
			} else {
				chars = append(chars, b)
			}
		}
	}

	err = reader.Err()
	if err != nil {
		panic(err)
	}

	fmt.Printf("Error sum: %d\n", errorSum)

}
