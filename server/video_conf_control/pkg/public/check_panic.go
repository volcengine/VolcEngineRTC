// Package public check checks panic
package public

import (
	logs "github.com/sirupsen/logrus"
	"runtime"
)

// const values
const (
	MaxStack = 5
)

// CheckPanic checks panics
func CheckPanic() {
	if err := recover(); err != nil {
		for i := 0; i <= MaxStack; i++ {
			if pc, file, line, ok := runtime.Caller(i); ok {
				f := runtime.FuncForPC(pc)
				logs.Errorf("panic error happened, stack:%d, med:%s, file:%s, line:%d, error:%s", i, f.Name(), file, line, err)
			}
		}
		logs.Errorf("panic error happened, error:%s", err)
	}
}
