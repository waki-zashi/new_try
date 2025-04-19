#pragma once

#include "Objects.h"  
#include "Point.h"

class Ocean;  

using namespace std;

struct Action
{
	Action(shared_ptr<Object> obj);
	virtual ~Action() = default;
	bool operator()(class Ocean& f) { return apply(f); }
	virtual bool apply(Ocean&) const = 0;

protected:
	shared_ptr<Object> obj;
};

struct NoAction : public Action
{
	NoAction(shared_ptr<Object> obj);

	bool apply(Ocean& ocean) const override;
};

struct TransformToReef : public Action
{
	TransformToReef(shared_ptr<Object> obj);

	bool apply(Ocean& ocean) const override;
};

struct TransformToStone : public Action
{
	TransformToStone(shared_ptr<Object> obj);

	bool apply(Ocean& ocean) const override;
};

struct Die : public Action
{
	Die(shared_ptr<Object> obj);

	bool apply(Ocean& ocean) const override;
};

struct Move : public Action
{
	Move(shared_ptr<Object> obj, Point to, int rad);

	bool apply(Ocean& ocean) const override;

private:
	Point go_to;
	int radius;
};

struct MoveRand : public Action
{
	MoveRand(shared_ptr<Object> obj, int rad);

	bool apply(Ocean& ocean) const override;

private:
	int radius;
};


struct Hunt : public Action
{
	Hunt(shared_ptr<Object> obj, Point to) : Action{ obj }, prey{ to } {}

	bool apply(Ocean& ocean) const override;

private:
	Point prey;
};