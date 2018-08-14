/*
 * nwsh
 * By end222
 * File: variables.hpp
 */

/*
 * variables represents all kinds of variables (arrays and non arrays)
 */
class variables {
	private:
		char* name;
	public:
		void change_value(char* var)
			{
				this.values[0] = var;
				this.num = 1;
			}
}

/*
 * var_array represents variables that are arrays
 */
class var_array : public variables
{
	private:
		int num; // Number of values stored
		char* values[100]; // Value or values of the variable
	public:
		var_array(char* name)
		{
			this.num = 0;
			this.name = name;
		}
		
		/*
		 * Add a new value to a variable
		 */
		void addValue(char* var)
		{
			this.values[this.num] = var;
			this.num++;
		}
		
		
}

/*
 * var_non_array represents variables that are nor arrays
 */
class var_non_array : public variables
{
}
