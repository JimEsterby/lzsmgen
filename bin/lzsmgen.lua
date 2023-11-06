-- lzsmgen.lua
json = require 'lunajson'
cgen = require 'codegen'

-- Empty tables
states = {}
transitions = {}
diagram = {}

--[[  reset
Reset global variables. ]]
function reset()
	states = {}
	transitions = {}
	diagram = {}
end

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

--[[  write_diagram()
Write the diagram information to file indicated by the argument name. The
information is in JSON format. ]]
function write_diagram(name)
	local result = false
	local t = {}
	t.states = states
	t.transitions = transitions

	--print("Writing " .. name)
	local f = io.open(name, "w")
	if io.type(f) == "file" then
		f:write(json.encode(t) .. "\n")
		f:close()
		result = true
	else
		print("Error: Write to file failure\n")
	end

	return result
end

--[[  read_diagram()
Read contents of file indicated by argument name. If the file has correct
JSON format, the global, diagram, will contain the file contents as a Lua
table. ]]
function read_diagram(name)
	local result = false
	local text

	local f = io.open(name)
	if io.type(f) == "file" then
		text = f:read("a")
		result, diagram = pcall(json.decode, text)
		f:close()
	else
		print("Error: Read from file failure\n")
	end

	return result 
end

--[[  nr_states()
Return the number of states in the diagram table. Assumes a valid diagram
table. ]]
function nr_states()
	return #diagram.states
end

--[[  nr_transitions()
Return the number of transitions in the diagram table. Assumes a valid diagram
table. ]]
function nr_transitions()
	return #diagram.transitions
end

--[[  get_state()
Return characteristics of an individual state in the diagram table. ]]
function get_state(index)
	local name
	local entry  -- entry action
	local during  -- during action
	local position  -- location points
	local default

	name = diagram.states[index].name
	entry = diagram.states[index].entry
	during = diagram.states[index].during
	position = diagram.states[index].position
	default = diagram.states[index].default

	return name, entry, during, default, position[1], position[2], position[3], position[4]
end

--[[  get_transition()
Return individual transition in the diagram table. ]]
function get_transition(index)
	local name
	local condition  -- trigger
	local action  -- action
	local position  -- location points
	local priority

	name = diagram.transitions[index].name
	condition = diagram.transitions[index].condition
	action = diagram.transitions[index].action
	position = diagram.transitions[index].position
	priority = diagram.transitions[index].priority

	return name, condition, action, priority, position[1], position[2], position[3], position[4]
end

