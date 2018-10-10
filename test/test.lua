local cputime = require 'cputime'
print ('VERSION: ' .. cputime._VERSION)

local p_utime, p_stime, err = cputime.get_process_cputime()
assert(p_utime ~= nil and type(p_utime) == 'number', 'p_utime must be number, not nil')
assert(p_stime ~= nil and type(p_stime) == 'number', 'p_stime must be number, not nil')
assert(err == nil, 'err must be nil')

-- TODO test for get_thread_cputime()

print 'OK'
