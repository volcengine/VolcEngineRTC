package pinyin

import (
	"strings"

	"github.com/mozillazg/go-pinyin"
)

var args pinyin.Args

func init() {
	args = pinyin.NewArgs()

	args.Fallback = func(r rune, a pinyin.Args) []string {
		return []string{string(r)}
	}
}

func GetPinyin(hans string) string {
	pys := pinyin.Pinyin(hans, args)
	words := make([]string, len(pys))

	for _, py := range pys {
		words = append(words, py...)
	}

	return strings.Join(words, "")
}
