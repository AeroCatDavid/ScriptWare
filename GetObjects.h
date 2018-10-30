# GetObjects

static int custom_getobjects(int rL) {
	VMProtectBeginMutation("getobjects");

	if (is_lite)
	{
		print_output(RGB(255, 0, 0), "ERROR: game:GetObjects(asset) is not avaliable on Script-Ware Lite!");
		return 1;
	}

	try {
		std::string asset = r_lua_tolstring(rL, -1, 0);
		R_LUA_POP(rL, 1);

		int buffer = 0;
		int asd[] = { 0, 0, 0, 0, 0, 0 };
		int asd1[] = { 0, 0, 0, 0, 0, 0 };
		int asd2[] = { 0, 0, 0, 0, 0, 0 };


		int content = r_getcontent(content_provider, &buffer, &asset, (int)asd, (int)asd1, (int)asd2);
		std::istream* result = *(std::istream**)(content);
		auto* instance_vector = new std::vector<instance>;

		r_load_instances((int)asset.c_str(), result, instance_vector);

		for (auto yeet : *instance_vector)
		{
			r_push_object(rL, yeet.ptr, yeet.ext);
		}

		int size = instance_vector->size();
		return size;
	}

	catch (std::exception)
	{
		print_output(RGB(255, 0, 0), "GetObjects encountered an exception while running. It's meant to be ran with a string as the argument (game:GetObjects(string asset))");
	}

	catch (...)
	{
		print_output(RGB(255, 0, 0), "GetObjects encountered an exception while running. It's meant to be ran with a string as the argument (game:GetObjects(string asset))");
	}

	VMProtectEnd();
}

/* In the connect part i put this: */

XorS(a, "https://hastebin.com/raw/alisiduzog"); //You got to have XorS, sorry lmao. Search it up :)

r_lua_pushnumber(rL, (double)(DWORD)custom_getobjects);
	r_lua_pushcclosure(rL, (rlua_cclosure)hook, 1);
	r_lua_setfield((int)rL, LUA_GLOBALSINDEX, "GetObjects");
  
  /* Yep :D */
  
  # Loadstrings
  
  r_lua_pushnumber(rL, (double)(DWORD)rloadstring);
	r_lua_pushcclosure(rL, (rlua_cclosure)hook, 1);
	r_lua_setfield((int)rL, LUA_GLOBALSINDEX, "loadstring");
  
  static int rloadstring(int rL) {
	const char* script = r_lua_tolstring(rL, -1, 0);
	execute_script(rL, L, (PCHAR)script);
	return 0;
}
