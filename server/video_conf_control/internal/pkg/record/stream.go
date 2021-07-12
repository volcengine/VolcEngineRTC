package record

func genTargetStreams(users []string, screen string) streamList {
	res := make([]stream, 0)
	for idx, user := range users {
		res = append(res, stream{
			Index:  idx,
			UserID: user,
		})
	}
	if screen != "" {
		res = append(res, stream{
			Index:      len(users),
			UserID:     screen,
			StreamType: 1,
		})
	}
	return streamList{
		StreamList: res,
	}
}
