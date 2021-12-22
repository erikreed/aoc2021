package main

import (
	"bufio"
	"fmt"
	"os"
	"strconv"
	"strings"
)

type SubState struct {
	depth      int
	horizontal int
	aim        int
}

func main() {
	subPosition := SubState{0, 0, 0}
	file, err := os.Open("p2.txt")
	if err != nil {
		panic(err)
	}
	reader := bufio.NewScanner(file)
	for reader.Scan() {
		line := reader.Text()

		parts := strings.Split(line, " ")
		direction := parts[0]
		val, err := strconv.Atoi(parts[1])
		if err != nil {
			panic(err)
		}
		if direction == "forward" {
			subPosition.horizontal += val
			subPosition.depth += subPosition.aim * val
		} else if direction == "down" {
			subPosition.aim += val
		} else if direction == "up" {
			subPosition.aim -= val
		} else {
			panic(direction)
		}
		if subPosition.depth < 0 || subPosition.horizontal < 0 {
			fmt.Printf("%d, %d -- %s\n", subPosition.depth, subPosition.horizontal, line)
			panic("bad sub pos")
		}
	}

	err = reader.Err()
	if err != nil {
		panic(err)
	}
	prod := subPosition.depth * subPosition.horizontal
	fmt.Printf("depth=%d, hor=%d, prod=%d\n", subPosition.depth,
		subPosition.horizontal, prod)

}
