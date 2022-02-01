#include <custom/doom_map.h>
#include <custom/doom_data.h>

DoomMap::DoomMap() {
	this->render_tree = new RenderTree();
}

void DoomMap::init(unsigned int width_, unsigned int height_) {
	
}

// Updates the values of the mapsector using the values of the parent sector
void DoomMap::compileSector(mapsector_t* sector) {

}

// Add the mapsector to the respective node in the tree
bool DoomMap::addSectorToRenderTree(mapsector_t* sector) {
	if (this->render_tree->isRootNodeNull())
	{
		
	}
	return true;
}

void DoomMap::update() {

}
void DoomMap::render() {

}