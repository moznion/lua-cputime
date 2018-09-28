local cputime = require 'cputime'
print ('VERSION: ' .. cputime._VERSION)

local utime, stime, cutime, cstime, err = cputime.get_cputime()

assert(utime ~= nil and type(utime) == 'number', 'utime must be number, not nil')
assert(stime ~= nil and type(stime) == 'number', 'stime must be number, not nil')
assert(cutime ~= nil and type(cutime) == 'number', 'cutime must be number, not nil')
assert(cstime ~= nil and type(cstime) == 'number', 'cstime must be number, not nil')
assert(err == nil, 'err must be nil')

print 'OK'
