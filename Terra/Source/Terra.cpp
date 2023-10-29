
#include "Prime/Core/EntryPoint.h"

namespace Prime
{
	class TerraApplication : public Application
	{
	public:
		TerraApplication(ApplicationSpec& spec)
			: Application(spec)
		{

		}

		~TerraApplication() override
		{

		}

	private:

	};

	Application* CreateApplication()
	{
		ApplicationSpec spec;

		return new TerraApplication(spec);
	}
}