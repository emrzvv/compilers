package main

func foo(a int, b int) int {
	func() int {
		return 2
	}()
	return a + b
}
