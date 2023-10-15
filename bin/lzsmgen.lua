-- lzsmgen.lua
json = require 'lunajson'

-- Empty tables
states = {}
transitions = {}

--[[  file_exists()
Check for the existence of a file. This solution can be found on
stackoverflow.com. It's a fairly obvious implementation. It might be better to
use the LuaFileSystem (lfs) extension, but I'm trying to avoid dependencies. ]]
function file_exists(name)
	local f = io.open(name, "r")
	if f ~= nil then
		io.close(f)
		return true
	else
		return false
	end
end

--[[  create_position()
Create lua table that is an array of 4 integers. ]]
function create_position(x1, y1, x2, y2)
	local t = { x1, y1, x2, y2 }

	return t
end

--[[  create_state()
Create a lua table representing a state. (Easier to do in Lua than C++]) Add
result to the global "states" table. ]]
function create_state(name, entry, during, default, position)
	local t = {}
	t.name = name
	t.entry = entry
	t.during = during
	t.default = default
	t.position = position
	table.insert(states, t)
end

--[[  create_transition()
Create a lua table representing a transition. (Easier to do in Lua than C++])
Add result to the global "transitions" table. ]]
function create_transition(name, condition, action, priority, position)
	local t = {}
	t.name = name
	t.condition = condition
	t.action = action
	t.priority = priority
	t.position = position
	table.insert(transitions, t)
end

--[[  write_diagram
Write the diagram information to file indicated by the argument name. The
information is in JSON format. ]]
function write_diagram(name)
	local result = false
	local t = {}
	t.states = states
	t.transitions = transitions

	--print("Writing " .. name)
	f = io.open(name, "w")
	if io.type(f) == "file" then
		f:write(json.encode(t) .. "\n")
		f:close()
		result = true
	else
		print("Error: Write to file failure\n")
	end

	return result
end
