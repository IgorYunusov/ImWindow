
#ifndef __IM_WINDOW_MANAGER_H__
#define __IM_WINDOW_MANAGER_H__

#include "ImwConfig.h"
#include "ImwWindow.h"
#include "ImwPlatformWindow.h"

#include <imgui/imgui.h>

#include <list>

#ifdef _DEBUG
#	if _WIN64
#		pragma comment (lib, "ImWindow_x64_Debug.lib")
#	else
#		pragma comment (lib, "ImWindow_Win32_Debug.lib")
#	endif
#else // _DEBUG
#	if _WIN64
#		pragma comment (lib, "ImWindow_x64_Release.lib")
#	else
#		pragma comment (lib, "ImWindow_Win32_Release.lib")
#	endif
#endif // _DEBUG

namespace ImWindow
{
	class ImwWindowManager
	{
		friend class ImwWindow;
		friend class ImwPlatformWindow;
		friend class ImwContainer;

		struct DockAction
		{
			ImwWindow*				m_pWindow;
			// Is Dock or Float
			bool					m_bFloat;
			//For Docking
			ImwWindow*				m_pWith;
			EDockOrientation		m_eOrientation;
			ImwPlatformWindow*		m_pToPlatformWindow;
		};

		struct DrawWindowAreaAction
		{
			DrawWindowAreaAction( ImwPlatformWindow* pWindow, const ImVec2& oRectPos, const ImVec2& oRectSize, const ImColor& oColor );
			ImwPlatformWindow*		m_pWindow;
			ImVec2					m_oRectPos;
			ImVec2					m_oRectSize;
			ImColor					m_oColor;
		};
	public:
		ImwWindowManager();
		virtual								~ImwWindowManager();

		bool								Init();
		bool								Run();
		void								Exit();

		ImwPlatformWindow*					GetMainPlatformWindow();

		void								SetMainTitle(const char* pTitle);

		void								Dock(ImwWindow* pWindow, EDockOrientation eOrientation = E_DOCK_ORIENTATION_CENTER, ImwPlatformWindow* pToPlatformWindow = NULL);
		void								DockWith(ImwWindow* pWindow, ImwWindow* pWithWindow, EDockOrientation eOrientation = E_DOCK_ORIENTATION_CENTER);
		void								Float(ImwWindow* pWindow);

		const ImwWindowList&				GetWindowList() const;
		ImwPlatformWindow*					GetCurrentPlatformWindow();
		ImwPlatformWindow*					GetWindowParent(ImwWindow* pWindow);
	protected:
		virtual ImwPlatformWindow*			CreatePlatformWindow(bool bMain, ImwPlatformWindow* pParent, bool bDragWindow) = 0;
		virtual void						InternalRun() = 0;
		virtual ImVec2						GetCursorPos() = 0;

		void								AddWindow(ImwWindow* pWindow);
		void								RemoveWindow(ImwWindow* pWindow);
		void								DestroyWindow(ImwWindow* pWindow);
		void								InternalDock(ImwWindow* pWindow, EDockOrientation eOrientation, ImwPlatformWindow* pToPlatformWindow);
		void								InternalDockWith(ImwWindow* pWindow, ImwWindow* pWithWindow, EDockOrientation eOrientation);
		void								InternalFloat(ImwWindow* pWindow);
		void								InternalUnDock(ImwWindow* pWindow);

		void								OnClosePlatformWindow(ImwPlatformWindow* pWindow);

		void								DrawWindowArea( ImwPlatformWindow* pWindow, const ImVec2& oPos, const ImVec2& oSize, const ImColor& oColor );

		void								Update();
		void								Paint(ImwPlatformWindow* pWindow);

		void								StartDragWindow(ImwWindow* pWindow);
		void								StopDragWindow();
		
		ImwPlatformWindow*					m_pMainPlatformWindow;
		ImwPlatformWindowList				m_lPlatformWindows;
		ImwPlatformWindow*					m_pDragPlatformWindow;
		ImwWindowList						m_lWindows;
		ImwWindowList						m_lOrphanWindows;
		ImwWindowList						m_lToDestroyWindows;
		ImwPlatformWindowList				m_lToDestroyPlatformWindows;
		ImwList<DockAction*>				m_lDockAction;
		ImwList<DrawWindowAreaAction>		m_lDrawWindowAreas;
		ImwPlatformWindow*					m_pCurrentPlatformWindow;
		ImwWindow*							m_pDraggedWindow;

		// Static
	public:
		static ImwWindowManager*			GetInstance();
	protected:
		static ImwWindowManager*			s_pInstance;
	};
}


#endif // __IM_WINDOW_MANAGER_H__