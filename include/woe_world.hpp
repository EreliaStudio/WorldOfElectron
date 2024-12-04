#pragma once

#include "sparkle.hpp"

#include "woe_entity.hpp"

struct Node
{
	spk::Color color = spk::Color::black;
	bool isObstacle = false;
};

struct Chunk
{
	static inline const spk::Vector2UInt Size = spk::Vector2UInt(16, 16);
	static inline const size_t MaxLayer = 3;

	int content[16][16][3];
	std::vector<spk::SafePointer<Entity>> entities;

	Chunk()
	{
		for (size_t i = 0; i < Size.x; i++)
		{
			for (size_t j = 0; j < Size.y; j++)
			{
				for (size_t h = 0; h < MaxLayer; h++)
				{
					content[i][j][h] = (h == 0 && (i == 0 || j == 0) ? 1 : 0);
				}
			}
		}
	}

	void serialize(char *p_data)
	{
		memcpy(p_data, content, sizeof(Chunk));
	}

	void deserialize(const char *p_data)
	{
		memcpy(content, p_data, sizeof(Chunk));
	}

	static spk::Vector2Int convertWorldToChunkPosition(const spk::Vector2Int& p_worldPosition)
	{
		return (spk::Vector2Int(spk::Vector2::floor(p_worldPosition / 16)));
	}

	static spk::Vector2Int absoluteToRelativePosition(const spk::Vector2Int& p_absolutePosition)
	{
		return (spk::Vector2Int(
			spk::positiveModulo(p_absolutePosition.x, 16),			
			spk::positiveModulo(p_absolutePosition.y, 16)	
		));
	}
};

class World
{
private:
	std::array<Node, 256> _nodes;
	std::unordered_map<spk::Vector2Int, Chunk> _chunks;
	std::unordered_map<Entity::ID, Entity> _entities;

public:
	World()
	{
		_nodes[0] = {.color = spk::Color(255, 255, 255, 0), .isObstacle = false};
		_nodes[1] = {.color = spk::Color(255, 0, 0, 255), .isObstacle = true};
		_nodes[2] = {.color = spk::Color(0, 255, 0, 255), .isObstacle = true};
		_nodes[3] = {.color = spk::Color(0, 0, 255, 255), .isObstacle = true};
	}

	const std::array<Node, 256>& nodes() const
	{
		return (_nodes);
	}

	spk::SafePointer<Node> node(const size_t& p_nodeIndex)
	{
		if (p_nodeIndex >= _nodes.size())
		{
			return (nullptr);
		}
		return (&(_nodes[p_nodeIndex]));
	}

	const std::unordered_map<spk::Vector2Int, Chunk> chunks() const
	{
		return (_chunks);
	}

	spk::SafePointer<Chunk> requestChunk(const spk::Vector2Int& p_chunkPosition)
	{
		return (&(_chunks[p_chunkPosition]));
	}

	spk::SafePointer<Chunk> chunk(const spk::Vector2Int& p_chunkPosition)
	{
		if (_chunks.contains(p_chunkPosition) == false)
		{
			return (nullptr);
		}
		return (&(_chunks[p_chunkPosition]));
	}

	const std::unordered_map<Entity::ID, Entity> entities() const
	{
		return (_entities);
	}

	spk::SafePointer<Entity> requestEntity(const Entity::ID& p_id)
	{
		return (&(_entities[p_id]));
	}

	spk::SafePointer<Entity> entity(const Entity::ID& p_id)
	{
		if (_entities.contains(p_id) == false)
		{
			return (nullptr);
		}
		return (&(_entities[p_id]));
	}
};