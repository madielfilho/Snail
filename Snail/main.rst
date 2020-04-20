stm SimCommunication {
	var neighs : St * St * St * St, location: int * int
	var updated : boolean = false , got : boolean = false
	input context { 
		uses ConnectionI
	    uses getStatusI
	}
	output context { 
		uses ConnectionI
	uses UpdateI }
	cycleDef cycle == 1initial i0
	
	state SInit {
	}
	state SConnected {
	}
	state SGet {
		initial i0
		state SInit {
		}
		transition t0 {
			from i0
			to SInit
		}
	}
	state SUpdate {
	initial i0
		state SInit {
		}
		final f0
		transition t0 {
			from i0
			to SInit
			action $updateReq
		}
	transition t1 {
			from SInit
			to f0
			action $updateFiware!location; updated = true
		}
	}
	transition t0 {
		from i0
		to SInit
	}
	transition t1 {
		from SInit
		to SConnected
		condition $connect
		action $connect_ack
	}
	
	transition SInit_to_SInit {
		from SInit
		to SInit
		condition not $connect
		action exec
	}
transition SConnected_to_SGet {
		from SConnected
		to SGet
		condition $get
	}
	
	transition SConnected_to_SConnected {
		from SConnected
		to SConnected
		condition not $get
		action exec
	}
transition SConnected_to_SUpdate {
		from SConnected
		to SUpdate
	}
transition SUpdate_to_SConnected {
		from SUpdate
		to SConnected
		condition updated==true
	}
transition SConnected_to_SConnected2 {
		from SConnected
		to SConnected
		condition not $update
		action exec
	}
}

