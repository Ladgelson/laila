import Axios from 'axios'
import { API_URL } from "../config";

const isNull = v => v == null || v == undefined;

export class Service {

  constructor(baseURL) {
    this.request = Axios.create({ 
      baseURL: API_URL + baseURL
    });
  }

  async findAll(params = {}, config = {}) {
    return this.request
      .get("", {
        params,
        ...config
      })
      .then(r => r.data);
  }

  async findById(id, params = {}, config = {}) {
    if (isNull(id)) {
      throw new TypeError(
        `Nenhum ID foi passado para ${this.constructor.name}#findById().`
      );
    }

    return this.request
      .get(`${id}`, {
        params,
        ...config
      }).then(r => r.data);
  }

  async update(data, params = {}, config = {}) {
    if (isNull(data)) {
      throw new TypeError(
        `Nenhum dado foi passado para ${this.constructor.name}#update()`
      );
    }
    
    if (isNull(data.id)) {
      throw new TypeError(
        `O campo data.id não foi passado para ${this.constructor.name}#update()`
      );
    }

    return this.request
      .patch(data.id, data, {
        params,
        ...config
      }).then(r => r.data);
  }

  async create(data, params = {}, config = {}) {
    if (isNull(data)) {
      throw new TypeError(
        `Nenhum dado foi enviado para ${this.constructor.name}#create()`
      )
    }

    delete data.id
    return this.request
      .post("", data, {
        params,
        ...config
      })
      .then(r => r.data);
  }

}