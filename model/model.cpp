#include "model.h"
#include "DataBase/databasemanager.h"

Model* Model::s_pModel = nullptr;

Model *Model::getInstance()
{
    if(s_pModel == nullptr)
        s_pModel = new Model();

    return s_pModel;
}

int Model::rowCount(const QModelIndex &parent) const
{
    return m_data.size();
}

QVariant Model::data(const QModelIndex &index, int role) const
{
    if(!index.isValid())
        return QVariant();

    int row = index.row();
    _Model_Data data = m_data.at(row);
    switch(role)
    {
    case _MODEL_COLUMN::_MODEL_id:
        return data.id;
    case _MODEL_COLUMN::_MODEL_welder_id:
        return data.welder_id;
    case _MODEL_COLUMN::_MODEL_create_time:
        return data.create_time;
    case _MODEL_COLUMN::_MODEL_energy:
        return data.energy;
    case _MODEL_COLUMN::_MODEL_amplitude:
        return data.amplitude;
    case _MODEL_COLUMN::_MODEL_pressure:
        return data.pressure;
    case _MODEL_COLUMN::_MODEL_time_alpha:
        return data.time_alpha;
    case _MODEL_COLUMN::_MODEL_time_beta:
        return data.time_beta;
    case _MODEL_COLUMN::_MODEL_power_alpha:
        return data.power_alpha;
    case _MODEL_COLUMN::_MODEL_power_beta:
        return data.power_beta;
    case _MODEL_COLUMN::_MODEL_pre_height_alpha:
        return data.pre_height_alpha;
    case _MODEL_COLUMN::_MODEL_pre_height_beta:
        return data.pre_height_beta;
    case _MODEL_COLUMN::_MODEL_post_height_alpha:
        return data.post_height_alpha;
    case _MODEL_COLUMN::_MODEL_post_height_beta:
        return data.post_height_beta;
    case _MODEL_COLUMN::_MODEL_force_alpha:
        return data.force_alpha;
    case _MODEL_COLUMN::_MODEL_force_beta:
        return data.force_beta;
    case _MODEL_COLUMN::_MODEL_residual_alpha:
        return data.residual_alpha;
    case _MODEL_COLUMN::_MODEL_residual_beta:
        return data.residual_beta;
    case _MODEL_COLUMN::_MODEL_current_sample_count:
        return data.current_sample_count;
    default:
        return QVariant();
    }
}

QHash<int, QByteArray> Model::roleNames() const
{
    QHash<int, QByteArray> roles;

    roles[_MODEL_COLUMN::_MODEL_id]                    = "id";
    roles[_MODEL_COLUMN::_MODEL_welder_id]             = "welder_id";
    roles[_MODEL_COLUMN::_MODEL_create_time]           = "create_time";
    roles[_MODEL_COLUMN::_MODEL_energy]                = "energy";
    roles[_MODEL_COLUMN::_MODEL_amplitude]             = "amplitude";
    roles[_MODEL_COLUMN::_MODEL_pressure]              = "pressure";
    roles[_MODEL_COLUMN::_MODEL_time_alpha]            = "time_alpha";
    roles[_MODEL_COLUMN::_MODEL_time_beta]             = "time_beta";
    roles[_MODEL_COLUMN::_MODEL_power_alpha]           = "power_alpha";
    roles[_MODEL_COLUMN::_MODEL_power_beta]            = "power_beta";
    roles[_MODEL_COLUMN::_MODEL_pre_height_alpha]      = "pre_height_alpha";
    roles[_MODEL_COLUMN::_MODEL_pre_height_beta]       = "pre_height_beta";
    roles[_MODEL_COLUMN::_MODEL_post_height_alpha]     = "post_height_alpha";
    roles[_MODEL_COLUMN::_MODEL_post_height_beta]      = "post_height_beta";
    roles[_MODEL_COLUMN::_MODEL_force_alpha]           = "force_alpha";
    roles[_MODEL_COLUMN::_MODEL_force_beta]            = "force_beta";
    roles[_MODEL_COLUMN::_MODEL_residual_alpha]        = "residual_alpha";
    roles[_MODEL_COLUMN::_MODEL_residual_beta]         = "residual_beta";
    roles[_MODEL_COLUMN::_MODEL_current_sample_count]  = "current_sample_count";

    return roles;
}

QVariant Model::getModelDataByWelderID(int welderID, int role) const
{
    for(int i = 0; i < m_data.size(); ++i)
    {
        if(m_data.at(i).welder_id != welderID)
            continue;

        switch(role)
        {
        case _MODEL_COLUMN::_MODEL_id:
            return m_data.at(i).id;
        case _MODEL_COLUMN::_MODEL_welder_id:
            return m_data.at(i).welder_id;
        case _MODEL_COLUMN::_MODEL_create_time:
            return m_data.at(i).create_time;
        case _MODEL_COLUMN::_MODEL_energy:
            return m_data.at(i).energy;
        case _MODEL_COLUMN::_MODEL_amplitude:
            return m_data.at(i).amplitude;
        case _MODEL_COLUMN::_MODEL_pressure:
            return m_data.at(i).pressure;
        case _MODEL_COLUMN::_MODEL_time_alpha:
            return m_data.at(i).time_alpha;
        case _MODEL_COLUMN::_MODEL_time_beta:
            return m_data.at(i).time_beta;
        case _MODEL_COLUMN::_MODEL_power_alpha:
            return m_data.at(i).power_alpha;
        case _MODEL_COLUMN::_MODEL_power_beta:
            return m_data.at(i).power_beta;
        case _MODEL_COLUMN::_MODEL_pre_height_alpha:
            return m_data.at(i).pre_height_alpha;
        case _MODEL_COLUMN::_MODEL_pre_height_beta:
            return m_data.at(i).pre_height_beta;
        case _MODEL_COLUMN::_MODEL_post_height_alpha:
            return m_data.at(i).post_height_alpha;
        case _MODEL_COLUMN::_MODEL_post_height_beta:
            return m_data.at(i).post_height_beta;
        case _MODEL_COLUMN::_MODEL_force_alpha:
            return m_data.at(i).force_alpha;
        case _MODEL_COLUMN::_MODEL_force_beta:
            return m_data.at(i).force_beta;
        case _MODEL_COLUMN::_MODEL_residual_alpha:
            return m_data.at(i).residual_alpha;
        case _MODEL_COLUMN::_MODEL_residual_beta:
            return m_data.at(i).residual_beta;
        case _MODEL_COLUMN::_MODEL_current_sample_count:
            return m_data.at(i).current_sample_count;
        default:
            return QVariant();
        }
    }

    return QVariant();
}

void Model::setModelData(int id, _MODEL_COLUMN column, QVariant data)
{
    for(int i = 0; i < m_data.size(); ++i)
    {
        if(m_data.at(i).id != id)
            continue;

        switch(column)
        {
        case _MODEL_COLUMN::_MODEL_id:
        {
            m_data[i].id = data.toInt();
            return;
        }
        case _MODEL_COLUMN::_MODEL_welder_id:
        {
            m_data[i].welder_id = data.toInt();
            return;
        }
        case _MODEL_COLUMN::_MODEL_create_time:
        {
            m_data[i].create_time = data.toString();
            return;
        }
        case _MODEL_COLUMN::_MODEL_energy:
        {
            m_data[i].energy = data.toInt();
            return;
        }
        case _MODEL_COLUMN::_MODEL_amplitude:
        {
            m_data[i].amplitude = data.toInt();
            return;
        }
        case _MODEL_COLUMN::_MODEL_pressure:
        {
            m_data[i].pressure = data.toInt();
            return;
        }
        case _MODEL_COLUMN::_MODEL_time_alpha:
        {
            m_data[i].time_alpha = data.toInt();
            return;
        }
        case _MODEL_COLUMN::_MODEL_time_beta:
        {
            m_data[i].time_beta = data.toInt();
            return;
        }
        case _MODEL_COLUMN::_MODEL_power_alpha:
        {
            m_data[i].power_alpha = data.toInt();
            return;
        }
        case _MODEL_COLUMN::_MODEL_power_beta:
        {
            m_data[i].power_beta = data.toInt();
            return;
        }
        case _MODEL_COLUMN::_MODEL_pre_height_alpha:
        {
            m_data[i].pre_height_alpha = data.toInt();
            return;
        }
        case _MODEL_COLUMN::_MODEL_pre_height_beta:
        {
            m_data[i].pre_height_beta = data.toInt();
            return;
        }
        case _MODEL_COLUMN::_MODEL_post_height_alpha:
        {
            m_data[i].post_height_alpha = data.toInt();
            return;
        }
        case _MODEL_COLUMN::_MODEL_post_height_beta:
        {
            m_data[i].post_height_beta = data.toInt();
            return;
        }
        case _MODEL_COLUMN::_MODEL_force_alpha:
        {
            m_data[i].force_alpha = data.toInt();
            return;
        }
        case _MODEL_COLUMN::_MODEL_force_beta:
        {
            m_data[i].force_beta = data.toInt();
            return;
        }
        case _MODEL_COLUMN::_MODEL_residual_alpha:
        {
            m_data[i].residual_alpha = data.toInt();
            return;
        }
        case _MODEL_COLUMN::_MODEL_residual_beta:
        {
            m_data[i].residual_beta = data.toInt();
            return;
        }
        case _MODEL_COLUMN::_MODEL_current_sample_count:
        {
            m_data[i].current_sample_count = data.toInt();
            return;
        }
        default:
            return;
        }
    }
}

void Model::save()
{
    DataBaseManager::getInstance()->clearModel();
    DataBaseManager::getInstance()->openTransaction();


    for(int i = 0; i < m_data.size(); ++i)
        DataBaseManager::getInstance()->insertModelRow(m_data.at(i));

    DataBaseManager::getInstance()->closeTransaction();
}

Model::Model(QObject *parent)
    : QAbstractListModel{parent}
{
    m_data = DataBaseManager::getInstance()->getModelData();
}
