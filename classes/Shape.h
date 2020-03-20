namespace DPDrawing {
	class Shape {
		private:
			int width;
			int height;
			int posX;
			int posY;

		public:
			virtual float getArea() = 0;
			void setWidth(int width) {
				this->width = width;
			}
			void setHeight(int height) {
				this->height = height;
			}
			void setPosX(int posX) {
				this->posX = posX;
			}
			void setPosY(int posY) {
				this->posY = posY;
			}
	};
}
