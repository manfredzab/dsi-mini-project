#ifndef STATUS_H_
#define STATUS_H_

namespace c875114
{

/**
 * Status enumerator, typically used to inform the caller about the success/failure of the callee.
 * Supported status values include success (kOK), failure (kFail) or lack of implementation (kNotImplemented).
 */
enum Status
{
  kOK = 0,
  kFail,
  kNotImplemented
};

} /* namespace c875114 */

#endif /* STATUS_H_ */
