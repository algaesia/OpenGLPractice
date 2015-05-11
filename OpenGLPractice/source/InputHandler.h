#ifndef _INPUT_HANDLER_H
#define _INPUT_HANDLER_H

class InputHandler
{
public:
	static InputHandler& Instance();

	bool CheckKeyDown(int a_KeyCode);
	bool CheckKeyHeld(int a_KeyCode);
private:
	InputHandler();

	InputHandler(InputHandler&) = delete;
	void operator=(InputHandler&) = delete;

	//true only for first frame
	bool IsKeyDown[300];

	//true when key is pressed (first frame and held)
	bool IsKeyHeld[300];
};

#endif