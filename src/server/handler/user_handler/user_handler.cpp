#include "user_handler.h"

user_handler::user_handler() {

}

user_handler::user_handler(utility::string_t url)
    : m_listener(url) {
    m_listener.support(methods::GET, &user_handler::handle_get);
    m_listener.support(methods::POST, &user_handler::handle_post);
    m_listener.support(methods::PUT, &user_handler::handle_put);
    m_listener.support(methods::DELETE, &user_handler::handle_delete);
}

user_handler::~user_handler() {

}

// GET api/user/id
void user_handler::handle_get(http_request request) {

}

// POST api/user
void user_handler::handle_post(http_request request) {

}

// PUT api/user/id
void user_handler::handle_put(http_request request) {

}

// DELETE api/user/id
void user_handler::handle_delete(http_request request) {

}