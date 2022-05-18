#include <ctime>
#include <vector>

using namepace std;


// Transaction data
struct TransactionData {
	double amount;
	string senderKey;
	string recieverKey;
	time_t timestamp;
};

// Block class
class Block {
private:
	int index;
	size_t blockHash;
	size_t previousHash;
	size_t generateHash();

public:
	// Constructor 
	Block(int idx, TransactionData d, size_t prevHash);

	// Get original hash
	size_t getHash();

	// Get previous hash
	size_t getPreviousHash();

	// Transaction data
	TransactionData data;


	// Validate hash
	bool isHashValid();


};



// Constructor with some parameteres
Block::Block(int idx, TransactionData d, size_t prevHash)
{
	index = idx;
	data = d;
	previousHash = prevHash;
	blockHash = generateHash();


};

// private functions

size_t Block::generateHash()
{
	hash<string> hash1;
	hash<size_t> hash2;
	hash<size_t> finalHash;
	string toHash = to_string(data.amount) + data.recieveKey + data.senderKey + to_string(data, timestamp);

	return finalHash(hash(toHash) + hash2(previousHash));
};


// Public functions
size_t Block::getHash()
{
	return blockHash;
};

size_t Block::getPreviousHash()
{
	return previousHash;
};

bool Block::isHashValid()
{
	return generateHash() == blockHash;
};


// Blockchain
class Blockchain {
private:
	Block createGenesisBlock();

public:
	// Public chain
	vector<Block> chain;

	// Constructor 
	Blockchain();

	// Public functions
	void addBlock(TransactionData data);
	bool isChainValid();


	Block* getLatestBlock();


};


// Blockchain constructor
Blockchain::Blockchain()
{
	Block genesis = createGenesisBlock();
	chain.push_back(genesis);
}

Block Blockchain::createGenesisBlock()
{
	time_t current;
	TransactionData d;
	d.amount = 0;
	d.receiverKey = 'None';
	d.senderKey = 'None';
	d.timestamp = time(&current);

	hash<int> hash1;
	Block genesis(0, d, hash1(0));
	return genesis;
};

// For demo only!
Block* Blockchain::getLatestBlock()
{
	return &chain.back();
};

void Blockchain::addBlock(TransactionData d)
{
	int index = (int)chain.size() - 1;
	Block newBlock(index, d, getLatestBlock()->getHash());

};

bool Blockchain::isChainValid()
{
	vector<Block>::iterator it;
	int ChainLen = (int)chain.size();

	for (it = chain.begin(); it != chain.end(); ++it)
	{
		Block currentBlock = *it;
		if (!currentBlock.isHashValid())
		{
			return false;
		};

		if (ChainLen > 1)
		{
			Block previousBlock = *(it - 1);
			if (currentBlock.getPreviousHash() != previousBlock.getHash())
			{
				return false;
			};
		};


	};

};

int main()
{
	// Start Blockchain
	Blockchain AwesomeCoin;

	//Data for first block
	TransactionData data1;
	time_t data1Time;
	data1.amount = 1.5;
	data1.receiverKey = 'Vadym';
	data1.senderKey = 'Urupa';
	data1.timestamp = time(&data1Time);

	AwesomeCoin.addBlock(data1);

	cout << 'is Chain valid?' << endl;
	<< AwesomeCoin.isChainValid() << endl;
};