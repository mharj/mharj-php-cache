<?php
namespace cache;

class InMemoryCache extends Cache {
	private $data = array();
	public function getValue($key) {
		return $this->data[$key];
	}
	
	public function setValue($key, $value) {
		$this->data[$key] = $value;
	}

	public function haveValue($key) {
		return isset($this->data[$key]);
	}
	public function delete($key) {
		if ( $this->haveValue($key) ) {
			unset($this->data[$key]); 
		}
	}
}