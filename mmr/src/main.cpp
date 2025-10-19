#include <Geode/Geode.hpp>
#include <Geode/modify/MenuLayer.hpp>

using namespace geode::prelude;

class $modify(MyMenuLayer, MenuLayer) {
	$override
	bool init() {
		if (!MenuLayer::init())
		return false;

		auto value = Mod::get()->getSettingValue<bool>("toggle-mmr");
		auto mgvalue = Mod::get()->getSettingValue<bool>("toggle-moreGames");
		auto moreGamesMenu = this->getChildByID("more-games-menu");

		if (value) {

			if (moreGamesMenu) {
				if (!mgvalue) {
					moreGamesMenu->setVisible(false);
					moreGamesMenu->setPosition({-1000, 1000});
					
				}
			}
			else FLAlertLayer::create(
				"WARNING",
				 "Geometry Dash Loaded Inpropperly! Restart The Game For The Menu To Propperly Load!",
				  "OK"
				)->show();

			auto socialMediaMenu = this->getChildByID("social-media-menu");
			if (socialMediaMenu) {
				socialMediaMenu->setVisible(false);
				socialMediaMenu->setPosition({-1000, 1000});
			}

			auto profileMenu = this->getChildByID("profile-menu");
			if (profileMenu) {
				auto winSize = CCDirector::sharedDirector()->getWinSize();
				float profileOffsetX = 60.0f;
				float profileOffsetY = 5.0f;

				profileMenu->setAnchorPoint({0.0f, 1.0f});
				profileMenu->setPosition({winSize.width - profileOffsetX, winSize.height - profileOffsetY});
			}

			auto userName = this->getChildByID("player-username");
			if (userName) {
				auto winSize = CCDirector::sharedDirector()->getWinSize();
				float nameOffsetX = 70.0f;
				float nameOffsetY = 60.0f;

				userName->setAnchorPoint({0.0f, 1.0f});
				userName->setPosition({winSize.width - nameOffsetX, winSize.height - nameOffsetY});
			}

			auto bottomMenu = this->getChildByID("bottom-menu");
			auto sideMenu = this->getChildByID("side-menu");
			
			if (!sideMenu || !bottomMenu) {
				FLAlertLayer::create("WARNING", "The Bottom or side menu didnt load!", "OK")->show();
				return true;
			}

			if (sideMenu && bottomMenu) {
				auto childrenCopy = CCArray::create();
				for (auto child : CCArrayExt<CCNode*>(bottomMenu->getChildren())) {
					childrenCopy->addObject(child);
				}

				for (auto child : CCArrayExt<CCNode*>(childrenCopy)) {
					bottomMenu->removeChild(child, false);
					sideMenu->addChild(child);

					child->setAnchorPoint({0.5f, 0.5f});
					child->setScale(0.8f);
				}		

				float spacing = 10.f;
				int count = sideMenu->getChildrenCount();

				float totalHeight = 0.f;
				for (auto child : CCArrayExt<CCNode*>(sideMenu->getChildren()))
					totalHeight += child->getContentSize().height * child->getScaleY();

				totalHeight += spacing * (count - 1);

				float sideMenuOffsetY = 80.0f;
				float startY = sideMenu->getContentSize().height / 2.0f + totalHeight / 2.0f - sideMenuOffsetY;
				float centerX = sideMenu->getContentSize().width / 2.0f;

				for (auto child : CCArrayExt<CCNode*>(sideMenu->getChildren())) {
					float childHeight = child->getContentSize().height * child->getScaleY();
					startY -= childHeight / 2.0f;

					child->setPosition({centerX, startY});
					startY -= childHeight / 2.0f;
				}
			}
		}
		return true;
	}
};