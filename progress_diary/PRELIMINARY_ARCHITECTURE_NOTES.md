# Day 1 Planning

So, today we analyzed the necessary basic logic for all of the mandatory **and**
advanced tasks for `shell v2`. All of our basic logic analyses can be found
[here](https://docs.google.com/spreadsheets/d/1JkahMJVAtfIrZwWqXRYG96VYBetQsgOcX4Zdhv1RkaU/), although it's not riveting reading.

From our analyses there, we came to the conclusion that our basic program will loosely resemble what we've written below. At this point, all of this is subject to change.


```
int main()
{
	pre_work() /* checking for file as arg and .hshrc and doing the PS1 */	main_loop()
	main_loop()	
		getline(input)
		tokenize(line)
		make_commands() -> returns command class with logic, name, input, output attributes
		for command in commands:
			execute(commands)
	post_work() /* saving the history, freeing_shit */
	return (exit_status);
}
```
