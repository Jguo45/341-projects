#include "bookTree.h"
using namespace std;

int main(){
    BookTree bookTreeTest;
    WordTree wordTreeTest;

    cout << "-----WordTree Testing-----" << endl << endl;

    // Inserts into empty splay tree
    bookTreeTest.insert("j", "author1", "I give Pirrip as my father’s family name, on the authority of his tombstone and my sister,—Mrs. Joe Gargery, who married the blacksmith. As I never saw my father or my mother, and never saw any likeness of either of them (for their days were long before the days of photographs), my first fancies regarding what they were like were unreasonably derived from their tombstones. The shape of the letters on my father’s, gave me an odd idea that he was a square, stout, dark man, with curly black hair. From the character and turn of the inscription, “Also Georgiana Wife of the Above,” I drew a childish conclusion that my mother was freckled and sickly. To five little stone lozenges, each about a foot and a half long, which were arranged in a neat row beside their grave, and were sacred to the memory of five little brothers of mine,—who gave up trying to get a living, exceedingly early in that universal struggle,—I am indebted for a belief I religiously entertained that they had all been born on their backs with their hands in their trousers-pockets, and had never taken them out in this state of existence.");
    cout << "Insert j" << endl;
    cout << "Get Root: " << bookTreeTest.getRootKey() << endl;
    bookTreeTest.dump();

    // Inserts d
    // Zig Rotation
    bookTreeTest.insert("d", "author2", "Two other passengers, besides the one, were plodding up the hill by the side of the mail. All three were wrapped to the cheekbones and over the ears, and wore jack-boots. Not one of the three could have said, from anything he saw, what either of the other two was like; and each was hidden under almost as many wrappers from the eyes of the mind, as from the eyes of the body, of his two companions. In those days, travellers were very shy of being confidential on a short notice, for anybody on the road might be a robber or in league with robbers. As to the latter, when every posting-house and ale-house could produce somebody in “the Captain's” pay, ranging from the landlord to the lowest stable non-descript, it was the likeliest thing upon the cards. So the guard of the Dover mail thought to himself, that Friday night in November, one thousand seven hundred and seventy-five, lumbering up Shooter's Hill, as he stood on his own particular perch behind the mail, beating his feet, and keeping an eye and a hand on the arm-chest before him, where a loaded blunderbuss lay at the top of six or eight loaded horse-pistols, deposited on a substratum of cutlass.");
    cout << "Insert d" << endl;
    cout << "Get Root: " << bookTreeTest.getRootKey() << endl;
    bookTreeTest.dump();

    // Inserts g
    // Zag Zig Rotation
    bookTreeTest.insert("g", "author3", "“Hang the boy, can’t I never learn anything? Ain’t he played me tricks enough like that for me to be looking out for him by this time? But old fools is the biggest fools there is. Can’t learn an old dog new tricks, as the saying is. But my goodness, he never plays them alike, two days, and how is a body to know what’s coming? He ’pears to know just how long he can torment me before I get my dander up, and he knows if he can make out to put me off for a minute or make me laugh, it’s all down again and I can’t hit him a lick. I ain’t doing my duty by that boy, and that’s the Lord’s truth, goodness knows. Spare the rod and spile the child, as the Good Book says. I’m a laying up sin and suffering for us both, I know. He’s full of the Old Scratch, but laws-a-me! he’s my own dead sister’s boy, poor thing, and I ain’t got the heart to lash him, somehow. Every time I let him off, my conscience does hurt me so, and every time I hit him my old heart most breaks. Well-a-well, man that is born of woman is of few days and full of trouble, as the Scripture says, and I reckon it’s so. He’ll play hookey this evening, * and [* Southwestern for “afternoon”] I’ll just be obleeged to make him work, tomorrow, to punish him. It’s mighty hard to make him work Saturdays, when all the boys is having holiday, but he hates work more than he hates anything else, and I’ve got to do some of my duty by him, or I’ll be the ruination of the child.”");
    cout << "Insert g" << endl;
    cout << "Get Root: " << bookTreeTest.getRootKey() << endl;
    bookTreeTest.dump();

    // Inserts e
    // Zig Zag Rotation
    bookTreeTest.insert("e", "author4", "We played robber now and then about a month, and then I resigned.  All the boys did.  We hadn’t robbed nobody, hadn’t killed any people, but only just pretended.  We used to hop out of the woods and go charging down on hog-drivers and women in carts taking garden stuff to market, but we never hived any of them.  Tom Sawyer called the hogs “ingots,” and he called the turnips and stuff “julery,” and we would go to the cave and powwow over what we had done, and how many people we had killed and marked.  But I couldn’t see no profit in it.  One time Tom sent a boy to run about town with a blazing stick, which he called a slogan (which was the sign for the Gang to get together), and then he said he had got secret news by his spies that next day a whole parcel of Spanish merchants and rich A-rabs was going to camp in Cave Hollow with two hundred elephants, and six hundred camels, and over a thousand “sumter” mules, all loaded down with di’monds, and they didn’t have only a guard of four hundred soldiers, and so we would lay in ambuscade, as he called it, and kill the lot and scoop the things.  He said we must slick up our swords and guns, and get ready.  He never could go after even a turnip-cart but he must have the swords and guns all scoured up for it, though they was only lath and broomsticks, and you might scour at them till you rotted, and then they warn’t worth a mouthful of ashes more than what they was before.  I didn’t believe we could lick such a crowd of Spaniards and A-rabs, but I wanted to see the camels and elephants, so I was on hand next day, Saturday, in the ambuscade; and when we got the word we rushed out of the woods and down the hill.  But there warn’t no Spaniards and A-rabs, and there warn’t no camels nor no elephants.  It warn’t anything but a Sunday-school picnic, and only a primer-class at that.  We busted it up, and chased the children up the hollow; but we never got anything but some doughnuts and jam, though Ben Rogers got a rag doll, and Jo Harper got a hymn-book and a tract; and then the teacher charged in, and made us drop everything and cut.");
    cout << "Insert e" << endl;
    cout << "Get Root: " << bookTreeTest.getRootKey() << endl;
    bookTreeTest.dump();

    // Inserts o
    // Zag Zag -> Zag Rotation
    bookTreeTest.insert("o", "author5", "An invitation to dinner was soon afterwards dispatched; and already had Mrs. Bennet planned the courses that were to do credit to her housekeeping, when an answer arrived which deferred it all. Mr. Bingley was obliged to be in town the following day, and, consequently, unable to accept the honour of their invitation, etc. Mrs. Bennet was quite disconcerted. She could not imagine what business he could have in town so soon after his arrival in Hertfordshire; and she began to fear that he might be always flying about from one place to another, and never settled at Netherfield as he ought to be. Lady Lucas quieted her fears a little by starting the idea of his being gone to London only to get a large party for the ball; and a report soon followed that Mr. Bingley was to bring twelve ladies and seven gentlemen with him to the assembly. The girls grieved over such a number of ladies, but were comforted the day before the ball by hearing, that instead of twelve he brought only six with him from London—his five sisters and a cousin. And when the party entered the assembly room it consisted of only five altogether—Mr. Bingley, his two sisters, the husband of the eldest, and another young man.");
    cout << "Insert o" << endl;
    cout << "Get Root: " << bookTreeTest.getRootKey() << endl;
    bookTreeTest.dump();

    // Inserts a
    // Zig Zig -> Zig Rotation
    bookTreeTest.insert("a", "author6", "It was a queer sort of place—a gable-ended old house, one side palsied as it were, and leaning over sadly. It stood on a sharp bleak corner, where that tempestuous wind Euroclydon kept up a worse howling than ever it did about poor Paul’s tossed craft. Euroclydon, nevertheless, is a mighty pleasant zephyr to any one in-doors, with his feet on the hob quietly toasting for bed. “In judging of that tempestuous wind called Euroclydon,” says an old writer—of whose works I possess the only copy extant—“it maketh a marvellous difference, whether thou lookest out at it from a glass window where the frost is all on the outside, or whether thou observest it from that sashless window, where the frost is on both sides, and of which the wight Death is the only glazier.” True enough, thought I, as this passage occurred to my mind—old black-letter, thou reasonest well. Yes, these eyes are windows, and this body of mine is the house. What a pity they didn’t stop up the chinks and the crannies though, and thrust in a little lint here and there. But it’s too late to make any improvements now. The universe is finished; the copestone is on, and the chips were carted off a million years ago. Poor Lazarus there, chattering his teeth against the curbstone for his pillow, and shaking off his tatters with his shiverings, he might plug up both ears with rags, and put a corn-cob into his mouth, and yet that would not keep out the tempestuous Euroclydon. Euroclydon! says old Dives, in his red silken wrapper—(he had a redder one afterwards) pooh, pooh! What a fine frosty night; how Orion glitters; what northern lights! Let them talk of their oriental summer climes of everlasting conservatories; give me the privilege of making my own summer with my own coals.");
    cout << "Insert a" << endl;
    cout << "Get Root: " << bookTreeTest.getRootKey() << endl;
    bookTreeTest.dump();

    // getWordHeight Test
    // Returns 0
    cout << "--- getWordHeight - Title: d, Word: a ---" << endl;
    cout << bookTreeTest.getWordHeight("d", "a") << endl;

    // makeSplay on find Test
    // Returns d
    cout << "--- Testing makeSplay on find ---" << endl;
    cout << bookTreeTest.getRootKey() << endl;

    cout << "-----WordTree Testing-----" << endl << endl;
    
    cout << "===Testing LL Rebalance===" << endl;
    wordTreeTest.insert("h");
    wordTreeTest.insert("c");
    wordTreeTest.insert("a");
    wordTreeTest.dump();
    cout << endl << "===Testing RR Rebalance===" << endl;
    wordTreeTest.insert("w");
    wordTreeTest.insert("y");
    wordTreeTest.dump();
    cout << endl << "===Testing RL Rebalance===" << endl;
    wordTreeTest.insert("n");
    wordTreeTest.dump();
    cout << endl << "===Testing LR Rebalance===" << endl;
    wordTreeTest.insert("g");
    wordTreeTest.dump();
    cout << endl;

    // find Test
    // Returns w
    cout << "--- find w Test ---" << endl;
    cout << wordTreeTest.find("w")->getValue() << endl;

    // searchCount Test
    // Returns 1
    cout << "--- searchCount w Test ---" << endl;
    cout << wordTreeTest.searchCount("w") << endl;

    // getRootHeight Test
    // Returns 2
    cout << "--- getRootHeight Test ---" << endl;
    cout << wordTreeTest.getRootHeight() << endl;

    return 0;
}