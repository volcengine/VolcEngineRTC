package custom_error

import "errors"

var (
	ErrInput                  = NewCustomError(400, errors.New("input format error"))
	ErrUserIsActive           = NewCustomError(402, errors.New("user is active"))
	ErrUserIsInactive         = NewCustomError(404, errors.New("user is inactive"))
	ErrUserExceedLimit        = NewCustomError(406, errors.New("user exceed limit"))
	ErrSameDeviceState        = NewCustomError(408, errors.New("same device state, no need to change"))
	ErrInvalidAppID           = NewCustomError(410, errors.New("app id is invalid"))
	ErrUserIsSharing          = NewCustomError(412, errors.New("user is sharing"))
	ErrUserIsNotHost          = NewCustomError(416, errors.New("user is not host"))
	ErrCanNotReconnect        = NewCustomError(418, errors.New("can not reconnect"))
	ErrRoomIsInactive         = NewCustomError(422, errors.New("room is inactive"))
	ErrRoomNotExist           = NewCustomError(422, errors.New("room not exist"))
	ErrHostNotAllowedLeave    = NewCustomError(420, errors.New("host is now allowed to leave meeting"))
	ErrMatchAntiDirt          = NewCustomError(430, errors.New("match anti dirt"))
	ErrorCodeExpiry           = NewCustomError(440, errors.New("verification code expired"))
	ErrorMessageCode          = NewCustomError(441, errors.New("verification code is incorrect"))
	ErrorTokenExpiry          = NewCustomError(450, errors.New("login token expired"))
	ErrorTokenEmpty           = NewCustomError(451, errors.New("login token empty"))
	ErrTokenGenerate          = NewCustomError(702, errors.New("generate token error"))
	ErrUnknownConnectionState = NewCustomError(500, errors.New("unknown connection state"))
	ErrLockRedis              = NewCustomError(500, errors.New("lock redis room error"))
	ErrUnknownUserState       = NewCustomError(500, errors.New("unknown user state"))
	ErrMuteAll                = NewCustomError(503, errors.New("mute all users error"))
	ErrChangeHost             = NewCustomError(504, errors.New("change host error"))
	ErrRoomAlreadyExist       = NewCustomError(530, errors.New("room already exist"))
)

type CustomError struct {
	err  error
	code int
}

func NewCustomError(code int, err error) *CustomError {
	return &CustomError{
		code: code,
		err:  err,
	}
}

func InternalError(err error) *CustomError {
	return &CustomError{
		code: 500,
		err:  err,
	}
}

func (e *CustomError) Error() string {
	return e.err.Error()
}

func (e *CustomError) Code() int {
	return e.code
}
