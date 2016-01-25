#pragma once

using namespace System::Threading;

// Implementation of C#'s lock(object){} taking advantage of managed destruction to enter and exit a mutex

ref class Lock {
	Object^ m_pObject;
public:
	Lock(Object ^ pObject) : m_pObject(pObject) {
		Monitor::Enter(m_pObject);
	}
	~Lock() {
		Monitor::Exit(m_pObject);
	}
};