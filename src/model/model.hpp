/**
 * @file       <model.hpp>
 * @brief      This header file holds implementation of Model class. 
 * 
 *             This calss implements model needed for successfull completion of laboratory work 1.
 *
 * @author     Alexander Chudnikov (THE_CHOODICK)
 * @date       15-02-2023
 * @version    0.0.1
 * 
 * @warning    This library is under development, so there might be some bugs in it.  
 * @bug        Currently, there are no any known bugs. 
 * 
 *             In order to submit new ones, please contact me via admin@redline-software.xyz.
 * 
 * @copyright  Copyright 2023 Alexander. All rights reserved. 
 * 
 *             (Not really)
 */
#ifndef MODEL_HPP
#define MODEL_HPP


#include <chrono>
#include <cstddef>
#include <cstring> // strcmp has better performance 
#include <iomanip>
#include <iostream>
#include <optional>
#include <functional>
#include <list>
#include <optional>
#include <string>
#include <type_traits>
#include <vector>


#include <filesystem>
#include <fstream>
#include <boost/json.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

#include <bitset>

#include "../model/model.hpp"

class Model;

class Hashing
{
public:
    static std::uint32_t basic_hashing_function(const std::string& value);
    static std::uint32_t djb2_hashing_function(const std::string& value);
    static std::uint32_t advanced_hashing_function(const std::string& value);

    static std::uint32_t count_collisions(const std::vector<std::list<Model>>& hash_table);

    static std::vector<std::list<Model>> hash_model(std::vector<Model>& model_vector, std::function<std::size_t(const std::string& value)> hash_function);

    static std::optional<Model> find_in_hash_table(const std::vector<std::list<Model>>& hash_table, std::uint32_t hash, std::size_t size);
};

class ModelComp;

class Model
{
public:
    Model(std::string full_name, std::string department, std::string job_title, std::chrono::year_month_day employment_date, std::uint32_t model_hash = 0, std::uint8_t hash_field = 255, const std::optional<std::function<std::size_t(const std::string& value)>>& optional_func = std::nullopt);
    Model(std::string full_name, std::string department, std::string job_title, std::string employment_date, std::uint32_t model_hash = 0, std::uint8_t hash_field = 255, const std::optional<std::function<std::size_t(const std::string& value)>>& optional_func = std::nullopt);
    Model(std::uint8_t decor_type);
    Model(const Model& other) {
    try {
        this->_full_name = other._full_name;
        this->_department = other._department;
        this->_job_title = other._job_title;
        this->_employment_date = other._employment_date;
        this->_decor_type = other._decor_type;
        this->_hash_field = other._hash_field;
        this->_model_hash = other._model_hash;
    } catch (const std::exception& e) {
        std::cout << e.what() << std::endl;
    }
}

    ~Model();

    void set_model(std::string full_name, std::string department, std::string job_title, std::chrono::year_month_day employment_date, std::uint32_t model_hash = 0, std::uint8_t hash_field = 255, const std::optional<std::function<std::size_t(const std::string& value)>>& optional_func = std::nullopt);
    void set_model(std::string full_name, std::string department, std::string job_title, std::string employment_date, std::uint32_t model_hash = 0, std::uint8_t hash_field = 255, const std::optional<std::function<std::size_t(const std::string& value)>>& optional_func = std::nullopt);
    
    void set_decor(std::uint8_t decor_type);
    void set_hash_func(std::function<std::size_t(const std::string& value)> hash_fucntion);
    void set_hash(std::uint32_t model_hash);
    void set_hash_field(std::uint8_t hash_field);

    ModelComp compare_type(const Model& r_model, std::uint8_t mode);

    template<typename T>
    ModelComp compare_type(std::uint8_t mode, T r_value);

    template<typename T>
    T get_field(std::uint8_t field) const;
    
    template<typename T>
    void set_field(std::uint8_t field, T value);

    std::uint32_t get_hash() const;
    std::uint8_t get_hash_field() const;

    template<typename T>
    T get_hash_field() const;

    static void save_model(const std::vector<Model>& model_vector, std::filesystem::path file_path);
    static void load_model(std::vector<Model>& model_vector, std::filesystem::path file_path);
    static void print_model(const std::vector<Model>& model_vector);

    friend std::ostream& operator<< (std::ostream& stream, const Model& model);

    friend ModelComp     operator<  (const Model& l_model, const Model& r_model);
    friend ModelComp     operator>  (const Model& l_model, const Model& r_model);
    friend ModelComp     operator<= (const Model& l_model, const Model& r_model);
    friend ModelComp     operator>= (const Model& l_model, const Model& r_model);

    friend ModelComp     operator== (const Model& l_model, const Model& r_model);
    friend ModelComp     operator!= (const Model& l_model, const Model& r_model);

private:
    std::string                     _full_name;
    std::string                     _department;
    std::string                     _job_title;
    std::chrono::year_month_day     _employment_date;

    std::uint8_t                    _decor_type;

    //HASHING
    std::uint8_t                    _hash_field;

    std::uint32_t                   _model_hash;
};

class ModelComp 
{
public:
    ModelComp();
    ModelComp(std::uint8_t value);
    ~ModelComp();

    void set_type_masked(std::uint8_t value, std::uint8_t offset);

    void set_name_type(std::uint8_t value);
    void set_dept_type(std::uint8_t value);
    void set_jobt_type(std::uint8_t value);
    void set_date_type(std::uint8_t value);

    std::uint8_t get_type_masked(std::uint8_t offset) const;

    std::uint8_t get_name_type() const;
    std::uint8_t get_dept_type() const;
    std::uint8_t get_jobt_type() const;
    std::uint8_t get_date_type() const;

    friend ModelComp operator== (const ModelComp& l_bool, const ModelComp& r_bool);
    friend ModelComp operator!= (const ModelComp& l_bool, const ModelComp& r_bool);

    friend std::ostream& operator<< (std::ostream& stream, const ModelComp& model);

    ModelComp operator! () const;

private:
    std::uint8_t _value;
};


template<typename T>
ModelComp Model::compare_type(std::uint8_t mode, T r_value)
{
    int8_t comp_result = 4;
    ModelComp model_comp;
    
    if (mode > 3)
    {
        mode = 0;
    }

    switch (mode)
    {
    case 0:
        {
            if (std::is_same<T, decltype(this->_full_name)>::value)
            {
                comp_result = this->_full_name.compare(r_value);
                if (comp_result < 0)
                {
                    comp_result = 1;
                }
                else if(comp_result > 0)
                {
                    comp_result = 2;
                }
                else 
                {
                    comp_result = 0;
                }
            }
            else 
            {
                throw std::invalid_argument("r_value should be _full_name");
            }
            model_comp.set_name_type(comp_result);
            break;
        }
    case 1:
        {
            if (std::is_same<T, decltype(this->_department)>::value)
            {
                comp_result = this->_department.compare(r_value);
                if (comp_result < 0)
                {
                    comp_result = 1;
                }
                else if(comp_result > 0)
                {
                    comp_result = 2;
                }
                else 
                {
                    comp_result = 0;
                }
            }
            else 
            {
                throw std::invalid_argument("r_value should be _department");
            }
            model_comp.set_dept_type(comp_result);
            break;
        }
    case 2:
        {
            if (std::is_same<T, decltype(this->_job_title)>::value)
            {
                comp_result = this->_job_title.compare(r_value);
                if (comp_result < 0)
                {
                    comp_result = 1;
                }
                else if(comp_result > 0)
                {
                    comp_result = 2;
                }
                else 
                {
                    comp_result = 0;
                }
            }
            else 
            {
                throw std::invalid_argument("r_value should be _job_title");
            }
            model_comp.set_jobt_type(comp_result);
            break;
        }
    case 3:
        {

            throw std::invalid_argument("r_value should be _employment_date");
            model_comp.set_date_type(comp_result);
            break;
        }
    default:
        {
            break;
        }
    }

    return model_comp;
}

template<typename T>
T Model::get_field(std::uint8_t field) const
{
    switch (field)
    {
        
        case 1:
        {   if (std::is_same<T, decltype(this->_department)>::value)
            {
                return this->_department;
            }
            else 
            {
                throw std::invalid_argument("T should be _department");
            }
            break;
        }

        case 2:
        {   if (std::is_same<T, decltype(this->_job_title)>::value)
            {
                return this->_job_title;
            }
            else 
            {
                throw std::invalid_argument("T should be _job_title");
            }
            break;
        }

        case 3:
        {   
            throw std::invalid_argument("T should be _employment_date");
            break;
        }

        default:
        {   if (std::is_same<T, decltype(this->_full_name)>::value)
            {
                return this->_full_name;
            }
            else 
            {
                throw std::invalid_argument("T should be _full_name");
            }
            break;
        }

    }
}


template<typename T>
void Model::set_field(std::uint8_t field, T value)
{
    switch (field)
    {
        
        case 1:
        {   if (std::is_same<T, decltype(this->_department)>::value)
            {
                this->_department = value;
            }
            else 
            {
                throw std::invalid_argument("T should be _department");
            }
            break;
        }

        case 2:
        {   if (std::is_same<T, decltype(this->_job_title)>::value)
            {
                this->_job_title = value;
            }
            else 
            {
                throw std::invalid_argument("T should be _job_title");
            }
            break;
        }

        case 3:
        {   
            throw std::invalid_argument("T should be _employment_date");
            break;
        }

        default:
        {   if (std::is_same<T, decltype(this->_full_name)>::value)
            {
                this->_full_name = value;
            }
            else 
            {
                throw std::invalid_argument("T should be _full_name");
            }
            break;
        }

    }
}

template<typename T>
T Model::get_hash_field() const
{
    return this->get_field<T>(this->_hash_field);
}

#endif // MODEL_HPP