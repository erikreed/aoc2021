package main

import (
	"bufio"
	"fmt"
	"os"
	"sort"
)

/*
): 1 point.
]: 2 points.
}: 3 points.
>: 4 points.
*/
func scoreLookup(c byte) int {
	if c == '(' {
		return 1
	}
	if c == '[' {
		return 2
	}
	if c == '{' {
		return 3
	}
	if c == '<' {
		return 4
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

	var scores []int64

	for reader.Scan() {
		line := reader.Text()
		var chars []byte
		corrupt := false
		for i := 0; i < len(line); i++ {
			b := line[i]
			if closing(b) {
				bFlipped := flipped(b)
				if len(chars) == 0 || chars[len(chars)-1] != bFlipped {
					corrupt = true
					break
				} else {
					chars = chars[:len(chars)-1]
				}
			} else {
				chars = append(chars, b)
			}
		}
		if corrupt {
			continue
		}

		var sum int64 = 0
		for i := len(chars) - 1; i >= 0; i-- {
			sum *= 5
			sum += int64(scoreLookup(chars[i]))
		}
		scores = append(scores, sum)
	}

	err = reader.Err()
	if err != nil {
		panic(err)
	}

	sort.Slice(scores, func(i, j int) bool { return scores[i] < scores[j] })

	if len(scores)%2 != 1 {
		panic("unimplemented")
	}
	median := scores[len(scores)/2]
	fmt.Printf("Error median: %d\n", median)

}
