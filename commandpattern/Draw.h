#pragma once

namespace DPDrawing {
	class Draw {
		public:
			void TakeDrawRequest(DrawShape* DrawRequest);
			void ExecuteDrawRequest();
	};
}