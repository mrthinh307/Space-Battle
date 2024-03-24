
Tools* aGoldItem = new Tools();
aGoldItem->setTexture(aGoldItem->getGoldItem());
if(aGoldItem != NULL){
                            x = p_threat->getPos().x; 
                            y = p_threat->getPos().y;        
                            aGoldItem->setPos(x, y);
                            goldItems.push_back(aGoldItem);                    
}
else{
        delete aGoldItem;
}
                        


                            