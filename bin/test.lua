-- test.lua
luaunit = require('luaunit')

require 'lzsmgen'  -- unit under test

-- KAN-19
function testWriteHeader001()
	luaunit.assertIsFunction(cgen.write_header)
end

-- KAN-19
function testWriteHeader002()
	luaunit.assertEquals(cgen.write_header("test002"), true)
end

-- KAN-19
function testWriteHeader003()  -- Windows
	luaunit.assertEquals(cgen.write_header([[..\demos\test003]]), true)
end

-- KAN-19
function testWriteHeader004()  -- Linux
	luaunit.assertEquals(cgen.write_header("../demos/test004"), true)
end

-- KAN-19
function testWriteHeader005()
	luaunit.assertEquals(cgen.write_header(""), false)
end

-- KAN-19
function testWriteSource001()
	luaunit.assertEquals(cgen.open_src("test002"), true);
	cgen.close_src()
end

os.exit( luaunit.LuaUnit.run() )
