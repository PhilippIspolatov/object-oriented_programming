#include "model.h"
#include "model_loadparts.h"


void ClearModel(sModel *mdl)
{
	ClearPointsList(&(mdl->points));
	ClearEdgesList(&(mdl->edges));
}


sModel* InitializeModel()
{
	sModel *mdl = new sModel;
	if (!mdl) return nullptr;

	mdl->edges.count = 0;
	mdl->edges.edgesArray = nullptr;
	mdl->points.count = 0;
	mdl->points.pointsArray = nullptr;
	return mdl;
}

eCodeFile LoadModelParts(sModel *&mdl, FILE *fl)
{
    eCodeFile res = TryLoadPoints(&(mdl->points), fl);

    if (res != cfFine)
    {
        fclose(fl);
        return res;
    }

    res = TryLoadEdges(&(mdl->edges), fl);
    fclose(fl);

    if (res != cfFine)
    {
        ClearPointsList(&(mdl->points));
        //return res;
    }

    return res;
}


eCodeFile LoadModel(sModel *&mdl, char *filename)
{
    eCodeFile res = cfFine;

	FILE *fl = fopen(filename, "r");
	if (!fl)
        res =  cfNotFound;


	sModel *newmodel = InitializeModel();

    if (!newmodel) res  = cfOutOfMemory;


    res = LoadModelParts(newmodel, fl);
    if (res != cfFine)
        return res;


	if (mdl)
	{
		ClearModel(mdl);
		delete mdl;
	}

    mdl = newmodel;

    return res;
}


eCodeFile SaveModel(sModel *&mdl, char *filename)
{
    eCodeFile res = cfFine;
    FILE *fl = fopen(filename, "w");
    if (!fl)
        res =  cfNotFound;

    res = SavePoints(mdl->points, fl);
    if (res == cfFine)
        res = SaveEdges(mdl->edges, fl);

    fclose(fl);

    return res;
}


eCodeFile FileProcess(sModel *&mdl, char *filename, eFileAction action)
{
    eCodeFile res = cfFine;
	switch(action)
	{
    case faLoad:
		{
            res =  LoadModel(mdl, filename);

		}
    case faSave:
		{
            res =  SaveModel(mdl, filename);
		}
	default:
		{
            res =  cfUnknownAction;
		}
	}
    return res;
}
