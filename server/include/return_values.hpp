#ifndef EXPLOIT_DEV_INCLUDE_RETURN_VALUES_HPP
#define EXPLOIT_DEV_INCLUDE_RETURN_VALUES_HPP

namespace return_value{

enum ServerReturnValues{
  kFailure = -1,
  kSuccess = 0
};

enum SendRecvData{
  kConnectionIssue = -1,
  kClientDisconnected = 0
};

}// namespace return_value
#endif// EXPLOIT_DEV_INCLUDE_RETURN_VALUES_HPP