#pragma once

#include "GLWindow.h"

#include <memory>
#include <stack>

class State;

class StateMachine {
	public:
		StateMachine();

		void run(std::unique_ptr<State> state);

		void nextState();
		void lastState();

		void updateEvents();
		void update();
		void render();

		bool running();
		void quit();

		template <typename T>
		static std::unique_ptr<T> buildState(StateMachine& machine, GLWindow& window, bool replace = true);

	private:
		// Stack of states
		std::stack<std::unique_ptr<State>> states;

		bool stateResume;
		bool stateRunning;
};

template <typename T>
std::unique_ptr<T> StateMachine::buildState(StateMachine& machine, GLWindow& glWindow, bool replace) {
	return std::unique_ptr<T>(new T(machine, glWindow, replace));
}
