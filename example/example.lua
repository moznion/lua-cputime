local cputime = require 'cputime'

local utime1, stime1, err = cputime.get_process_cputime()
if err ~= nil then
    print(err)
    os.exit(1)
end

local buf = ''
for i=0,500000 do
    buf = buf .. '*'
end

local utime2, stime2, err = cputime.get_process_cputime()
if err ~= nil then
    print(err)
    os.exit(1)
end

print('utime: ' .. utime2 - utime1 .. ' usec')
print('stime: ' .. stime2 - stime1 .. ' usec')
