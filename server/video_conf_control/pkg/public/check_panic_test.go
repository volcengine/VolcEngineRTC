package public

import (
	"sync"
	"testing"
)

func TestCheckPanic(t *testing.T) {
	CheckPanic()
	var wg sync.WaitGroup
	wg.Add(1)
	go func() {
		defer wg.Done()
		defer CheckPanic()
		panic("error, test CheckPanic")
	}()
	wg.Wait()
	t.Log("check panic done")
}
