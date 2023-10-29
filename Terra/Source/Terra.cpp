
#include "Prime/Core/EntryPoint.h"
#include "TerraLayer.h"

namespace Prime
{
	class TerraApplication : public Application
	{
	public:
		TerraApplication(ApplicationSpec& spec)
			: Application(spec)
		{
			LayerStack::PushLayer(new TerraLayer());
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