#include "entrypoint.h"
#include "conversions.h"
#include "render.h"
#include "model.h"
#include "actions.h"

eCodeFile Apply(eChangeAction action, uChangeData *data)
{
    static sRenderData changes;

    static sModel *model = InitializeModel();

	if (!model) return cfOutOfMemory;

	eCodeFile res = cfFine;

	switch (action)
	{

    case caLoad:
		{
            InitializeRenderData(&changes);
            res = FileProcess(model, data->filename, faLoad);
			break;
		}
    case caSave:
        {
            res = FileProcess(model, data->filename, faSave);
            return res;
        }
    case caScale:
		{
            ChangeScale(&changes, data->scale);
			break;
		}
    case caRotate:
		{
            ChangeRotation(&changes, data->move);
			break;
		}
    case caSetRot:
		{
            SetRotation(&changes, data->move);
			break;
		}
    case caShift:
		{
            ChangeShift(&changes, data->move);
			break;
		}
    case caDraw:
        {
            res = DrawModel(model, data->canvas, &changes);
            break;
        }
    case caDelete:
        {
            ClearModel(model);
            break;
        }

	default: 
        res =  cfUnknownAction;
	}

	return res;
}
