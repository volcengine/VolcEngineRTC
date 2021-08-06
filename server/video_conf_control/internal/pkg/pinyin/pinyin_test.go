package pinyin

import "testing"

func TestGetPinyin(t *testing.T) {
	for _, test := range []struct {
		hans   string
		pinyin string
	}{
		{
			hans:   "中国梦我的梦",
			pinyin: "zhongguomengwodemeng",
		},
		{
			hans:   "视频会议系统",
			pinyin: "shipinhuiyixitong",
		},
		{
			hans:   "为什么喜欢养猫",
			pinyin: "weishenmexihuanyangmao",
		},
		{
			hans:   "富强、民主、文明、和谐，自由、平等、公正、法治，爱国、敬业、诚信、友善",
			pinyin: "fuqiang、minzhu、wenming、hexie，ziyou、pingdeng、gongzheng、fazhi，aiguo、jingye、chengxin、youshan",
		},
		{
			hans:   "All things are difficult before they are easy.",
			pinyin: "All things are difficult before they are easy.",
		},
		{
			hans:   "123Never say die永不气馁",
			pinyin: "123Never say dieyongbuqinei",
		},
	} {
		result := GetPinyin(test.hans)
		if test.pinyin != result {
			t.Errorf("hans: %v, expect: %v, result: %v", test.hans, test.pinyin, result)
		}
	}
}
