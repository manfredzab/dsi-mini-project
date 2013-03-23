#ifndef STATUS_H_
#define STATUS_H_

namespace uk_ac_ox_cs_c875114
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

} /* namespace uk_ac_ox_cs_c875114 */

#endif /* STATUS_H_ */
